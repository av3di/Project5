#ifndef _POINTMODEL_H_
#define _POINTMODEL_H_

#include "Header.h"

class PointModel : public Model
{
protected:
	std::vector<double> v_xyz; // All vertex xyz coords in the obj file
	std::vector<double> c_rgb; // All rgb values in the obj file
	std::vector<double> n_xyz; // All normal xyz coords in the obj file
	std::vector<int> faces; 

	std::vector<double> v_minmax; // the smallest and largest vertex xyz values, respectively
	int objrows = 0; // Rows in the xyz file

public:
	PointModel();
	~PointModel();
	void draw();
	void parseFile(const char* filename);
	void findMinMax();
	void moveToOrigin();
	void fitToWindow();
};

#endif
