/*
input at most three movies, use structure store movie info which include year, title.
then output the result
 */
#include <stdio.h>

struct Movie{
        int year;
        char title[256];
};

int main(){
        Movie movies[3];
        int i;
        for(i=0; i<3; ++i){
                movies[i].year=0;
                scanf("%d", &movies[i].year);
                if(0 == movies[i].year)
                        break;

                scanf("%s", movies[i].title);
        }

        printf("number of movies = %d\n", i);
        for(int j=0; j<i; ++j){
                printf("movie %d,  year %d,  title: %s\n", i, movies[i].year, movies[i].title);
        }
        puts(movies[0].title);
}
