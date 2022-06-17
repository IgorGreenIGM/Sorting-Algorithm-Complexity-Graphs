#ifndef SOURIS_H_INCLUDED
#define SOURIS_H_INCLUDED

void OnClickOverTriBulles(int boutton, int status, int x, int y);

void OnClickOverTriSelection(int boutton, int state, int x, int y);

void OnClickOverTriInsertion(int boutton, int state, int x, int y);

void EraseRectCoordInfo(int x, int y);

void CreationZoneSouris(int cur_x, int cur_y, double rayon, int choix);

#endif // SOURIS_H_INCLUDED
