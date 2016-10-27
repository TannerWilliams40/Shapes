#include "Shapes.h" //decided to have a lot more fun with this style assignment because I'm so happy I finsihed this program
Color Shape::colorAtPoint(Shape* list[], const int num, const double a, const double b)
{
	for (int n = 0; n < num; n++)
	{
		if (list[n] -> inside(a,b))
			return (list[n] -> color());
	}
	return (Color)300;
}
std::string Shape::getcolor(const int a) const //brute forced because lack of time and understanding of enum class
{
	if (a == 0)
		return "BLACK";
	if (a == 1)
		return "RED";
	if (a == 2)
		return "GREEN";
	if (a == 3)
		return "YELLOW";
	if (a == 4)
		return "BLUE";
	if (a == 5)
		return "MAGENTA";
	if (a == 6)
		return "CYAN";
	if (a == 7)
		return "WHITE";
	return "INVALID";
}
void Box::move(const double a, const double b) //ordered pairs as top/bottom and left/right
{
	tb.x += b;
	tb.y += b;
	lr.x += a;
	lr.y += a;
}
double Box::perimeter() const // added sides and multiplied by 2 (nick and stephen seemed to think this wouldn't work...lol)
{
	return (((tb.x - tb.y) + (lr.y - lr.x))*2);
}
double Box::area() const //length times width...simple stuff
{
	return ((tb.x - tb.y) * (lr.y - lr.x));
}
void Box::render(std::ostream& os) const //ya know, printing stuff
{
	os << "Box(" << getcolor(color()) << "," << lr.x << "," << tb.x << "," << lr.y << "," << tb.y << ")";
}
bool Box::inside(const double a, const double b) const
{
	if ((a < lr.y && a > lr.x) && (b < tb.x && b > tb.y))
		return true;
	else
		return false;
}
void Circle::move(const double a, const double b) //ordered pair for center
{
	center.x += a;
	center.y += b;
}
double Circle::perimeter() const //increased places for pi early on when we had incorrect perimeter...
{
	return (2 * Cradius * M_PI);
}
double Circle::area() const //..oh well percision never hurt anyone
{
	return (M_PI * (Cradius * Cradius));
}
void Circle::render(std::ostream& os) const //printing, printing, just keep printing, what do you do? keep priiiiiinting
{
	os << "Circle(" << getcolor(color()) << "," << center.x << "," << center.y << "," << Cradius << ")";
}
bool Circle::inside(const double a, const double b) const
{
	if ((sqrt(pow((a - center.x), 2) + pow((b - center.y), 2))) < Cradius)
		return true;
	else
		return false;
}
void Triangle::move(const double a, const double b) //woohoo moving triangles. This coordinate thing was a great idea just saying
{
	p1.x += a;
	p2.x += a;
	p3.x += a;
	p1.y += b;
	p2.y += b;
	p3.y += b;
}
double Triangle::perimeter() const //distance formula three tiiiiiiimes hollaaaaaaa
{
	return ((sqrt(pow((p1.x - p2.x), 2) + pow((p1.y-p2.y), 2))) + (sqrt(pow((p2.x - p3.x), 2) + pow((p2.y-p3.y), 2))) + (sqrt(pow((p3.x - p1.x), 2) + pow((p3.y-p1.y), 2))));
}
double Triangle::area() const //forgot to divide this result by two and it gave me fits for ages. stupid formulas
{
	return (std::abs((p1.x*(p2.y-p3.y)+p2.x*(p3.y-p1.y)+p3.x*(p1.y-p2.y))/2));
}
void Triangle::render(std::ostream& os) const //Idk if I can come up with a better printing comment after that nemo reference...
{
	os << "Triangle(" << getcolor(color()) << "," << p1.x << "," << p1.y << "," << p2.x << "," << p2.y << "," << p3.x << "," << p3.y << ")";
}
bool Triangle::inside(const double a, const double b) const
{
	double stackarray[6];
	stackarray[0] = p1.x;
	stackarray[1] = p1.y;
	stackarray[2] = p2.x;
	stackarray[3] = p2.y;
	stackarray[4] = p3.x;
	stackarray[5] = p3.y;
	int i, j, c = 0;
	for (i = 0, j = 5; i < 6; j = i++) 
	{
		if ( ((stackarray[i+1]>b) != (stackarray[j+1]>b)) && (a < (stackarray[j]-stackarray[i]) * (b-stackarray[i+1]) / (stackarray[j+1]-stackarray[i+1]) + stackarray[i]) )
    	c = !c;
  	}
  return c;
}
Polygon::Polygon(const Color a, const double *pts, const int p): Shape(a) //creating a local copy of the array
{
	numpoints = p;
	newarray = new double[p*2];
	for (int n = 0; n < p*2; n++)
	{
		newarray[n] = pts[n];
	}
}
void Polygon::move(const double a, const double b) //two for loops, one for the x's (evens) and one for y's (odds)
{
	for (int n = 0; n < numpoints * 2; n+=2)
	{
		newarray[n] += a;
	}
	for (int nn = 1; nn < numpoints *2; nn +=2)
	{
		newarray[nn] += b;
	}
}
double Polygon::perimeter() const //defined n outside of for loop so i can use it when i wrap back to first point (see below)
{
	double sum = 0;
	int n = 0;
	for (; n < numpoints*2-2; n+=2)
	{
		sum += (sqrt(pow((newarray[n] - newarray[n+2]), 2) + pow((newarray[n+1]-newarray[n+3]), 2)));
	}				 	     //here								//and here
	sum += (sqrt(pow((newarray[n] - newarray[0]), 2) + pow((newarray[n+1]-newarray[1]), 2)));
	return sum;
}
double Polygon::area () const //literally same as perimeter just different formula
{
	double sum = 0;
	int n = 0;
	for (; n < numpoints*2-2; n+=2)
	{
		sum += (newarray[n]*newarray[n+3])-(newarray[n+2]*newarray[n+1]);
	}
	sum += (newarray[n]*newarray[1])-(newarray[n+1]*newarray[0]);
	return sum/2;
}
void Polygon::render(std:: ostream& os) const //trailing commas have been an issue since P1...got it fixed
{
	os << "Polygon(" << getcolor(color()) << "," << numpoints << ",";
	int n = 0;
	for (; n < numpoints*2-1; n++)
	{
		os << newarray[n] << ",";
	}

	os << newarray[n] << ")";
}
bool Polygon::inside(const double a, const double b) const
{

	int i, j, c = 0;
	for (i = 0, j = (numpoints*2)-1; i < (numpoints*2); j = i++) 
	{
			if ( ((newarray[i+1]>b) != (newarray[j+1]>b)) && (a < (newarray[j]-newarray[i]) * (b-newarray[i+1]) / (newarray[j+1]-newarray[i+1]) + newarray[i]) )
		c = !c;
	}
		return c;
}
Polygon::~Polygon() //deallocating the array cause can't leave it orphaned gotta just kill it
{
	delete [] newarray;
}
void Line::move(const double a, const double b)
{
	p1.x += a;
	p1.y += b;
	p2.x += a;
	p2.y += b;
}
double Line::perimeter() const
{
	return (sqrt(pow((p1.x - p2.x), 2) + pow((p1.y-p2.y), 2)));
}
void Line::render(std:: ostream& os) const
{
	os << "Line(" << getcolor(color()) << "," << p1.x << "," << p1.y << "," << p2.x << "," << p2.y << ")";
}
double RoundBox::perimeter() const
{
	Coordinates _lr;
	Coordinates _tb;
	_lr.x = left();
	_lr.y = right();
	_tb.x = top();
	_tb.y = bottom();
	double length = _lr.y - _lr.x - (Bradius*2);
	double width = _tb.x - _tb.y - (Bradius*2);
	return ((length*2) + (width*2) + (2*Bradius*M_PI));
}
double RoundBox::area() const
{
	Coordinates _lr;
	Coordinates _tb;
	_lr.x = left();
	_lr.y = right();
	_tb.x = top();
	_tb.y = bottom();
	double length = _lr.y - _lr.x - (Bradius*2);
	double width = _tb.x - _tb.y - (Bradius*2);
	return ((length*_tb.x) + (width*_lr.y) + ((Bradius*Bradius)*M_PI) - (width*length));
}
bool RoundBox::inside(const double a, const double b) const
{
	Coordinates _lr;
	Coordinates _tb;
	_lr.x = left();
	_lr.y = right();
	_tb.x = top();
	_tb.y = bottom();
	if ((a > _lr.x + Bradius && a < _lr.y - Bradius) && (b < _tb.x && b > _tb.y))
		return true;
	else if ((a > _lr.x && a < _lr.y) && (b < _tb.x - Bradius && b > _tb.y + Bradius))
		return true;
	else if ((sqrt(pow((a - (_lr.x + Bradius)), 2) + pow((b - (_tb.x - Bradius)), 2))) < Bradius)
		return true;
	else if ((sqrt(pow((a - (_lr.y - Bradius)), 2) + pow((b - (_tb.x - Bradius)), 2))) < Bradius)
		return true;
	else if ((sqrt(pow((a - (_lr.x + Bradius)), 2) + pow((b - (_tb.y + Bradius)), 2))) < Bradius)
		return true;
	else if ((sqrt(pow((a - (_lr.y - Bradius)), 2) + pow((b - (_tb.y + Bradius)), 2))) < Bradius)
		return true;
	else
		return false;
}
void RoundBox::render(std::ostream& os) const
{
	Coordinates _lr;
	Coordinates _tb;
	_lr.x = left();
	_lr.y = right();
	_tb.x = top();
	_tb.y = bottom();
	os << "RoundBox(" << getcolor(color()) << "," << _lr.x << "," << _tb.x << "," << _lr.y << "," << _tb.y << "," << Bradius << ")";
}
Group::Group(const Color a, const int gn, Shape* array1[]) : Shape(a)
{
	nums = gn;
	newgroup = new Shape*[gn];
	for (int n = 0; n < gn; n++)
	{
		newgroup[n] = array1[n];
		newgroup[n] -> color(a);
	}
}
void Group::shapes(const int gn, Shape** list)
{
	for (int n = 0; n < nums; n++)
	{
		delete newgroup[n];
	}
	delete [] newgroup;
	newgroup = new Shape*[gn];
	nums = gn;
	for (int n = 0; n < gn; n++)
	{
		newgroup[n] = list[n];
	}
}
void Group::move(const double a, const double b)
{
	for (int n = 0; n < nums; n++)
	{
		newgroup[n] -> move(a,b);
	}
}
double Group::perimeter() const
{
	double total = 0;
	for (int n = 0; n < nums; n++)
	{
		total+= newgroup[n] -> perimeter();
	}
	return total;
}
double Group::area() const
{
	double total = 0;
	for (int n = 0; n < nums; n++)
	{
		total+= newgroup[n] -> area();
	}
	return total;
}
void Group::render(std::ostream& os) const
{
	os << "Group(" << getcolor(Shape::color()) << "," << nums;
	for (int n = 0; n < nums; n++)
	{
		os << ",";
		newgroup[n] -> render((std::ostream&) os);
	}
	os << ")";
}
bool Group::inside(const double a, const double b) const
{
	for (int n = 0; n < nums; n++)
	{
		if (newgroup[n] -> inside(a,b) == true)
			return true;
	}
	return false;
}
void Group::color(const Color a)
{
	for (int n = 0; n < nums; n++)
	{
		newgroup[n] -> color(a);
	}
	Shape::color(a);
}
Group::~Group()
{
	for (int n = 0; n < nums; n++)
	{
		delete newgroup[n];
	}	
	delete [] newgroup;
}
