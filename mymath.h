#ifndef MYMATH_H
#define MYMATH_H

double getRadius(Sprite,Sprite);
double getTheta(Sprite,Sprite);
SDL_Rect moveOnAngle(Sprite R2, double distance, double theta);
SDL_Rect changeAngle(Sprite R1, Sprite R2, double changeInDegrees);

#endif // AUDIO_H
