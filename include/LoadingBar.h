#ifndef LOADINGBAR_H_INCLUDED
#define LOADINGBAR_H_INCLUDED

void DrawProgressBarBackground(double largeurBar, double hauteurBar, double side_margin, double topDown_margin);

void DrawProgressBar(int etat, int max, long double echelle, double largeurBar, double hauteurBar, double side_margin, double topDown_margin);

void CLearProgressBar(double largeurBar, double hauteurBar, double side_margin, double topDown_margin);

#endif // LOADINGBAR_H_INCLUDED
