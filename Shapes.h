#include <iostream>
#include <cmath>
#include "math.h"
enum Color { BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE, INVALID };
class Shape {
	public:
		//Constructor and desconstructor:
		Shape(Color a) : clr(a) {}
		virtual ~Shape() {}
		//shape functions:				
		virtual void color(const Color a) {clr = a;} //Set
		Color color() const {return clr;} //Get
		//virtuals because they are never defined for shape
		virtual double area() const = 0;
		virtual double perimeter() const = 0;
		virtual void move(const double a, const double b) = 0;
		virtual void render(std::ostream& os) const = 0;
		virtual bool inside(const double a, const double b) const = 0;
		double thickness() const {return area()/perimeter();}
		static Color colorAtPoint(Shape* list[], const int num, const double a, const double b);
	private:
		Color clr;
		Shape(const Shape& a); //to prevent people from breaking the world
		void operator=(const Shape& a);
	protected:
		std::string getcolor(const int a) const; //part of the brute force (see the cpp)
		struct Coordinates //best decision ever right here
		{
			double x;
			double y;
		};
};
class Box : public Shape
{
	public:
		Box(const Color a, const double l, const double t, const double r, const double b) : Shape(a) {lr.x=l; tb.x=t; lr.y=r; tb.y=b;}
		
		void move(const double a, const double b);
		double perimeter() const;
		double area() const;
		void render(std::ostream& os) const;
		bool inside(const double a, const double b) const;

		void left(const double a) {lr.x = a;} //set
		void right(const double a) {lr.y = a;} //set
		void top(const double a) {tb.x = a;} //set
		void bottom(const double a) {tb.y = a;} //set 
		double left() const {return lr.x;} //get
		double right() const {return lr.y;} //get
		double top() const {return tb.x;} //get
		double bottom() const {return tb.y;} //get
	private:
		Coordinates tb;
		Coordinates lr;
};
class Circle : public Shape
{
	public:
		Circle(const Color a, const double x, const double y, const double r) : Shape(a) {center.x=x; center.y=y; Cradius=r;}

		void move(const double a, const double b);
		double perimeter() const;
		double area() const;
		void render(std::ostream& os) const;
		bool inside(const double a, const double b) const;

		void centerX(const double a) {center.x=a;} //set
		void centerY(const double a) {center.y=a;} //set
		void radius(const double a) {Cradius=a;} //set
		double centerX () const {return center.x;} //get
		double centerY () const {return center.y;} //get
		double radius () const {return Cradius;} //get
	private:
		double Cradius;
		Coordinates center;
};
class Triangle : public Shape
{
	public:
		Triangle(const Color a, const double X, const double Y, const double XX, const double YY, const double XXX, const double YYY) : Shape(a) {p1.x=X; p1.y=Y; p2.x=XX; p2.y=YY; p3.x=XXX; p3.y=YYY;}
		
		void move(const double a, const double b);
		double perimeter() const;
		double area() const;
		void render(std::ostream& os) const;
		bool inside(const double a, const double b) const;

		void cornerX1(const double a) {p1.x=a;} //set
		void cornerX2(const double a) {p2.x=a;} //set
		void cornerX3(const double a) {p3.x=a;} //set
		void cornerY1(const double a) {p1.y=a;} //set
		void cornerY2(const double a) {p2.y=a;} //set
		void cornerY3(const double a) {p3.y=a;} //set
		double cornerX1() const {return p1.x;} //get
		double cornerX2() const {return p2.x;} //get
		double cornerX3() const {return p3.x;} //get
		double cornerY1() const {return p1.y;} //get
		double cornerY2() const {return p2.y;} //get
		double cornerY3() const {return p3.y;} //get
	private:
		Coordinates p1;
		Coordinates p2;
		Coordinates p3;
};
class Polygon : public Shape
{
	public:
		Polygon(const Color a, const double *pts, const int p);

		void move(const double a, const double b);
		double perimeter() const;
		double area () const;
		void render(std:: ostream& os) const;
		bool inside(const double a, const double b) const;

		void points(const int a) {numpoints = a;} //set
		int points() const {return numpoints;} //get
		double vertexX(const int vertex) const {return newarray[vertex*2];}
		double vertexY(const int vertex) const {return newarray[vertex*2+1];}
		void vertexX(const int vertex, double a) const {newarray[vertex*2] = a;}
		void vertexY(const int vertex, double a) const {newarray[vertex*2+1] = a;}

		~Polygon();
	private:
		int numpoints;
		double *newarray;
};
class Line : public Shape
{
	public:
		Line(const Color a, const double x, const double y, const double s, const double t) : Shape(a) {p1.x = x; p1.y = y; p2.x = s; p2.y = t;}

		void move(const double a, const double b);
		double perimeter() const;
		void render(std:: ostream& os) const;
		double area() const {return 0;}
		bool inside(const double a, const double b) const {double lol = a; double rofl = b; return false;}

		double end1X() const {return p1.x;}
		double end1Y() const {return p1.y;}
		double end2X() const {return p2.x;}
		double end2Y() const {return p2.y;}

		void end1X(const double p) {p1.x = p;}
		void end1Y(const double p) {p1.y = p;}
		void end2X(const double p) {p2.x = p;}
		void end2Y(const double p) {p2.y = p;}
	
	private:
		Coordinates p1;
		Coordinates p2;
};
class RoundBox : public Box
{
	public:
		RoundBox(const Color a, const double l, const double t, const double r, const double b, const double rad) : Box(a,l,t,r,b) {Bradius = rad;}
		
		double radius() const {return Bradius;}
		void radius(const double r) {Bradius = r;}

		double perimeter() const;
		double area() const;
		void render(std::ostream& os) const;
		bool inside(const double a, const double b) const;

	private:
		double Bradius;
};
class Group : public Shape
{
	public:
		Group(const Color a, const int gn, Shape** list);

		void move(const double a, const double b);
		double perimeter() const;
		double area() const;
		void render(std::ostream& os) const;
		bool inside(const double a, const double b) const;
		void shapes(const int gn, Shape** list);
		int shapes() const {return nums;}
		Shape* shape(const int i) const {return newgroup[i];}
		void color(const Color a);
		~Group();

	private:
		int nums;
		Shape** newgroup;

};
