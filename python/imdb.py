import omdb
omdb.set_default('apikey', '68f39148')
# movie = omdb.get(title='Guardians of the Galaxy Vol. 2')


def get_movie(movie):
    movie_stats = omdb.get(title=movie)
    if (movie_stats):
        for key, value in movie_stats.items():
                print(f'{key}: {value}')
        print('\n')
    else:
        print(f'"{movie}" not found')
    return None

def prompt_user():
    user_input = input('Type in title(s) you want to search for: ')
    while user_input != "end":
        if " : " in user_input:
            user_input = user_input.split(" : ")
            argument = user_input[-1]
            del user_input[-1]
            user_input = [title.split(', ') for title in user_input]
            for movie in user_input[0]:
                get_movie(movie)
        else:
            user_input = user_input.split(", ")
            for movie in user_input:
                get_movie(movie)

        user_input = input('Type in title(s) you want to search for: ')

prompt_user()
