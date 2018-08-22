import omdb
from datetime import datetime
omdb.set_default('apikey', '68f39148')


def get_movie(movie, movies):
    movie_stats = omdb.get(title=movie)

    if movie_stats and movie_stats not in movies:
        movies.append(movie_stats)

    return movies


def convert_data(movies):
    for movie in movies:
        if movie['released'] != 'N/A':
            movie['released'] = datetime.strptime(movie['released'], '%d %b %Y')
        else:
            movie['released'] = datetime.min
        movie['imdb_rating'] = float(movie['imdb_rating'])
        movie['imdb_votes'] = int(movie['imdb_votes'].replace(",", ""))
        movie['runtime'] = int(movie['runtime'].replace(" min", ""))

    return None


def sort_movies(movies, sort_by):
    sort_by = sort_by.lower()
    categories = {'rating': 'imdb_rating', 'length': 'runtime', 'release date': 'released', 'popularity': 'imdb_votes'}

    if sort_by in categories:
        convert_data(movies)
        movies.sort(key = lambda k: k[categories[sort_by]], reverse=True)

    return movies


def display_movies(movies):
    for movie in movies:
        for key, value in movie.items():
            print(f'{key}: {value}')
        print("\n")


def convert_date(movies):
    for movie in movies:
        if movie['released'] == datetime.min:
            movie['released'] = 'N/A'
        else:
            movie['released'] = movie['released'].strftime('%d.%m.%Y')

    return None


def prompt_user():
    user_input = input('Type in title(s) you want to search for: ')
    movies_catalog = []
    while user_input != "end":
        if " : " in user_input:
            user_input = user_input.split(" : ")
            argument = user_input[-1]
            del user_input[-1]
            user_input = [title.split(', ') for title in user_input]
            for movie in user_input[0]:
                get_movie(movie, movies_catalog)
            sort_movies(movies_catalog, argument)
            convert_date(movies_catalog)
            display_movies(movies_catalog)
        else:
            user_input = user_input.split(", ")
            for movie in user_input:
                get_movie(movie, movies_catalog)
            display_movies(movies_catalog)

        movies_catalog = []
        user_input = input('Type in title(s) you want to search for: ')


prompt_user()

