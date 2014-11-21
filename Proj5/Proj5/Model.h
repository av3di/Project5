#ifndef _MODEL_H_
#define _MODEL_H_

#include "Header.h"


class Model
{
protected:
	Matrix4 model2world;            // model matrix (transforms model coordinates to world coordinates)
	double angle;                   // rotation angle [degrees]
	bool counter;
public:

	Model();                // Constructor
	Model::~Model();         // Destructor
	Matrix4& getMatrix();
	virtual void draw();
	void spin(double);      // spin cube [degrees]
	void changeCounter();
	void translate(double, double, double);
	void scale(double, double, double);
	void rotate(Vector3 rotation_axis, double deg_angle);
	void rotateZ(double);
	void rotateY(double a);
	void reset();
};

#endif

