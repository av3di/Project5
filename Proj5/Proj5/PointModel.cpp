#include "Header.h"

PointModel::PointModel()
{
}


PointModel::~PointModel()
{
}

void PointModel::parseFile(const char* filename)
{
	// Create pointer to the xyz file
	FILE * objf;
	const char *bunnyfile = "bunny.obj";
	char c1;
	char c2;
	char comment[100];
	double x, y, z, r, g, b; // xyz vertex position, rgb vertex color
	int index1, index2, index3;
	errno_t err = fopen_s(&objf, filename, "r");
	if (err != 0)
	{
		cout << "The file " << filename << "could not be opened." << endl;
	}
	else
	{
		for (int row = 0; row < objrows; row++)
		{ 
			fscanf_s(objf, "%c", &c1, sizeof(c1));
			c2 = fgetc(objf); 
			if (c1 == 'v' && c2 == ' ') // vertex position and color
			{
				fscanf_s(objf, "%lf", &x, sizeof(x));
				fscanf_s(objf, "%lf", &y, sizeof(y));
				fscanf_s(objf, "%lf", &z, sizeof(z));
				if (strcmp(filename, bunnyfile) == 0) // we are dealing with the bunny file
				{
					fscanf_s(objf, "%lf", &r, sizeof(r));
					fscanf_s(objf, "%lf", &g, sizeof(g));
					fscanf_s(objf, "%lf", &b, sizeof(b));
				}
				else
				{
					r = 1; g = 1; b = 1;
				}
				v_xyz.push_back(x);
				v_xyz.push_back(y);
				v_xyz.push_back(z);
				c_rgb.push_back(r);
				c_rgb.push_back(g);
				c_rgb.push_back(b);
				fgets(comment, 100, objf);  // get the rest of the line
			}
			else if (c1 == 'v' && c2 == 'n') // vertex normal
			{
				fscanf_s(objf, "%lf", &x, sizeof(x));
				fscanf_s(objf, "%lf", &y, sizeof(y));
				fscanf_s(objf, "%lf", &z, sizeof(z));
				n_xyz.push_back(x);
				n_xyz.push_back(y);
				n_xyz.push_back(z);
				fgets(comment, 100, objf);  // get the rest of the line
			}
			else if (c1 == 'f' && c2 == ' ') // face
			{
				// format: f xx//xx yy//yy zz//zz
				fscanf_s(objf, "%d//", &index1, sizeof(index1));
				fscanf_s(objf, "%d", &index2, sizeof(index2));
				fscanf_s(objf, "%d//", &index2, sizeof(index2));
				fscanf_s(objf, "%d", &index3, sizeof(index3));
				fscanf_s(objf, "%d//", &index3, sizeof(index3));
				faces.push_back(index1);
				faces.push_back(index2);
				faces.push_back(index3);
				fgets(comment, 100, objf);  // get the comment line
			}
			else if (c1 == '#') // Comment
			{
				fgets(comment, 100, objf);  // get the comment line
			}
			//getchar();
		}
		fclose(objf);
		cout << "number of vertices coords (104,505) : " << v_xyz.size() << endl;
		cout << "number of normals (should be the same) : " << n_xyz.size() << endl;
	}
}
void PointModel::findMinMax()
{
	double xmin = 100, ymin = 100, zmin = 100;
	double xmax = -100, ymax = -100, zmax = -100;
	int count = 0;

	for (int count = 0; count + 2 < v_xyz.size(); count = count + 3)
	{
		//Find min and max x
		if (v_xyz[count] < xmin)
			xmin = v_xyz[count];

		if (v_xyz[count] > xmax)
			xmax = v_xyz[count];

		//Find min and max y
		if (v_xyz[count + 1] < ymin)
			ymin = v_xyz[count + 1];
		if (v_xyz[count + 1] > ymax)
			ymax = v_xyz[count + 1];

		// Find min and max z
		if (v_xyz[count + 2] < zmin)
			zmin = v_xyz[count + 2];
		if (v_xyz[count + 2] > zmax)
			zmax = v_xyz[count + 2];
	}
	v_minmax.push_back(xmin);
	v_minmax.push_back(xmax);
	v_minmax.push_back(ymin);
	v_minmax.push_back(ymax);
	v_minmax.push_back(zmin);
	v_minmax.push_back(zmax);

	cout << "Smallest x value is: " << xmin << endl;
	cout << "Largest x value is: " << v_minmax[1] << endl;

	cout << "Smallest y value is: " << ymin << endl;
	cout << "Largest y value is: " << v_minmax[3] << endl;

	cout << "Smallest z value is: " << zmin << endl;
	cout << "Largest z value is: " << v_minmax[5] << "\n" << endl;
}

void PointModel::moveToOrigin()
{
	findMinMax();
	double midx = (v_minmax[0] + v_minmax[1]) / 2;
	double midy = (v_minmax[2] + v_minmax[3]) / 2;
	double midz = (v_minmax[4] + v_minmax[5]) / 2;

	Matrix4 printTranslate;
	printTranslate.makeTranslate(midx * -1, midy * -1, midz * -1);
	printTranslate.print("Translate matrix is : ");
	cout << "\n " << endl;

	this->model2world = printTranslate * this->model2world;
}

void PointModel::fitToWindow()
{
	// theta to be passed into tan() must be in radians so convert
	double theta = (Globals::viewAngle / 2) / 180 * M_PI;

	// tan(theta) * (camera_distance * 2) / (xmax - xmin)
	double factor = tan(theta) * (abs(Globals::camZ) * 2) / (v_minmax[1] - v_minmax[0]);

	Matrix4 printScale;
	printScale.makeScale(factor, factor, factor);
	printScale.print("Scale matrix is: ");
	this->model2world = printScale * this->model2world;
}

void PointModel::draw()
{
	Vector3 normal;
	glBegin(GL_TRIANGLES);
	int index1;
	int index2;
	int index3;
	for (int count = 0; count + 2 < faces.size(); count = count+3)
	{
		index1 = (faces[count] - 1) * 3;
		index2 = (faces[count + 1] - 1) * 3;
		index3 = (faces[count + 2] - 1) * 3;

		glColor3d(c_rgb[index1], c_rgb[index1 + 1], c_rgb[index1 + 2]);
		normal.setX(n_xyz[index1]);
		normal.setY(n_xyz[index1 + 1]);
		normal.setZ(n_xyz[index1 + 2]);
		normal.normalize();
		glNormal3d(normal.getX(), normal.getY(), normal.getZ());
		glVertex3d(v_xyz[index1], v_xyz[index1 + 1], v_xyz[index1 + 2]);

		glColor3d(c_rgb[index2], c_rgb[index2 + 1], c_rgb[index2 + 2]);
		normal.setX(n_xyz[index2]);
		normal.setY(n_xyz[index2 + 1]);
		normal.setZ(n_xyz[index2 + 2]);
		normal.normalize();
		glNormal3d(normal.getX(), normal.getY(), normal.getZ());
		glVertex3d(v_xyz[index2], v_xyz[index2 + 1], v_xyz[index2 + 2]);

		glColor3d(c_rgb[index3], c_rgb[index3 + 1], c_rgb[index3 + 2]);
		normal.setX(n_xyz[index3]);
		normal.setY(n_xyz[index3 + 1]);
		normal.setZ(n_xyz[index3 + 2]);
		normal.normalize();
		glNormal3d(normal.getX(), normal.getY(), normal.getZ());
		glVertex3d(v_xyz[index3], v_xyz[index3 + 1], v_xyz[index3 + 2]);
	}
	glEnd();
	glFlush();
	glutSwapBuffers();
}
