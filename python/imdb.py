import omdb
from datetime import datetime
omdb.set_default('apikey', '68f39148')


def get_movie(movie, movies):
    '''
    Send request with movie title to imdb API
    :param movie: title of movie which we are looking for inside imdb
    :param movies: list of dictionaries to store movie details returned by imdb API
    :return: None
    '''
    movie_stats = omdb.get(title=movie) # send request to imdb API for given title

    if movie_stats and movie_stats not in movies: # if dictionary is not empty and is not in list of dictionaries
        movies.append(movie_stats) # add it to the list

    return None


def convert_data(movies):
    '''
    Convert release date, runtime, rating and popularity strings to non-string values
    so it's possible to sort the list of dictionaries by those values
    :param movies: list of dictionaries containing movie details
    :return: None
    '''
    for movie in movies:
        if movie['released'] != 'N/A': # some movies do not have release date
            movie['released'] = datetime.strptime(movie['released'], '%d %b %Y') # convert date in string format to datetime object
        else: # if movie does not have release date assign earliest date possible to enable sorting by date
            movie['released'] = datetime.min
        # Convert rating string to float, votes to integer without commas, and runtime to int without minutes
        movie['imdb_rating'] = float(movie['imdb_rating'])
        movie['imdb_votes'] = int(movie['imdb_votes'].replace(",", ""))
        movie['runtime'] = int(movie['runtime'].replace(" min", ""))

    return None


def sort_movies(movies, sort_by):
    '''
    Gets unsorted list of dictionary and category by which the list should be sorted,
    sorts the list and returns the list
    :param movies: list of dictionaries to be sorted
    :param sort_by: category by which the list should be sorted
    :return: sorted list by given category
    '''
    sort_by = sort_by.lower() # convert category to lowercase
    categories = {'rating': 'imdb_rating', 'length': 'runtime', 'release date': 'released', 'popularity': 'imdb_votes'} # categories given by user are different than value names in imdb API

    # If given category is in acceptable option
    if sort_by in categories:
        convert_data(movies) # Convert data inside the movies dictionaries
        movies.sort(key = lambda k: k[categories[sort_by]], reverse=True) # Sort the list by category in descending order

    # Return sorted list
    return movies


def display_movies(movies):
    '''
    Simply display movie attributes
    :param movies: list of dictionaries with movie details
    :return: None
    '''
    for movie in movies:
        for key, value in movie.items():
            print(f'{key}: {value}')
        print("\n")

    return None


def convert_date(movies):
    '''
    Converts date from "sorting date" to user-friendly date
    :param movies: list of movie dictionaries
    :return: None
    '''
    for movie in movies:
        if movie['released'] == datetime.min: # if movie does not have release date it gets earliest date possible
            movie['released'] = 'N/A' # convert it back to 'N/A' string
        else:
            movie['released'] = movie['released'].strftime('%d.%m.%Y') # else convert "sorting-date" to user-friendly date

    return None


def prompt_user():
    '''
    Prompts user for movie(s) title until the user types in "end"
    User can request sorted list by four categories:
        : Rating
        : Length
        : Release date
        : Popularity
    :return:
    '''
    user_input = input('Type in title(s) you want to search for: ') # first prompt user for title, if user types in "end" the whole loop is skipped
    movies_catalog = [] # list for storing movies dictionaries
    while user_input != "end": # as long as user does not type "end" keep asking and returning movies details
        if " : " in user_input: # if user typed in sorting argument
            user_input = user_input.split(" : ") # split the string to extract the argument
            argument = user_input[-1] # save it in separate variable
            del user_input[-1] # remove it from string containing movie(s) title string
            user_input = [title.split(', ') for title in user_input] # split movie titles into separate strings
            for movie in user_input[0]: # for each movie in the list
                get_movie(movie, movies_catalog) # send a request with the title and store dictionary in movies_catalog
            sort_movies(movies_catalog, argument) # sort the movies by given argument
            convert_date(movies_catalog) # convert the date to user-friendly format
            display_movies(movies_catalog) # display the movies
        else: # Else just get and display list of movies without any sorting
            user_input = user_input.split(", ")
            for movie in user_input:
                get_movie(movie, movies_catalog)
            display_movies(movies_catalog)

        # Reset movies catalog and prompt user again
        movies_catalog = []
        user_input = input('Type in title(s) you want to search for: ')


# Execute main function
prompt_user()

