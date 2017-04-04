#ifndef MYMATH_H
#define MYMATH_H

double getRadius(SDL_Rect,SDL_Rect);
double getTheta(SDL_Rect,SDL_Rect);
SDL_Rect moveOnAngle(SDL_Rect R2, double distance, double theta);
SDL_Rect changeAngle(SDL_Rect R1, SDL_Rect R2, double changeInDegrees);

#endif // AUDIO_H
