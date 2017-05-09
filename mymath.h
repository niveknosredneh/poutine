#ifndef MYMATH_H
#define MYMATH_H

double getRadius(SDL_Point,SDL_Point);
double getTheta(SDL_Point,SDL_Point);
SDL_Point moveOnAngle(SDL_Point, double distance, double theta);
SDL_Point changeAngle(SDL_Point, SDL_Point, double newRad, double changeInDegrees);

bool checkCollision(Sprite S1, Sprite S2);

#endif // AUDIO_H
