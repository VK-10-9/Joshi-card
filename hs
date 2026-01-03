6. Develop a JAVA program to create an abstract class Shape with abstract methods calculate Area() and calculate Perimeter(). Create subclasses Circle and Triangle that extend the Shape class and implement the respective methods to calculate the area and perimeter of each shape.
abstract class Shape
{
	public abstract double getArea();
	public abstract double getPerimeter();
}
class Circle extends Shape
{
	private double radius;
	public Circle(double radius)
	{ 
		this.radius = radius;
	}
	public double getArea() 
	{
		return Math.PI* radius * radius;
	}

	public double getPerimeter()
	{ 
		return 2 * Math.PI * radius;
	}
}
class Triangle extends Shape
{
	private double side1;
	private double side2; 
	private double side3;
	public Triangle(double side1, double side2, double side3)
	{
		this.side1 = side1;
		this.side2=side2; 
		this.side3=side3;
	}

	public double getArea()
	{
		double s =(side1 +side2 +side3)/ 2;
		return Math.sqrt(s* (s-side1)*(s-side2)*(s- side3));
	}

	public double getPerimeter()
	{
		return side1 + side2 + side3;
	}
}

public class Main 
{
public static void main(String[] args) 
{
		Shape rectangle = new Rectangle(10,12); 
		Shape circle = new Circle(5);
		Shape triangle = new Triangle(7,8,6);

// calculate area and perimeter of each shape 
		System.out.println("\nAreaandperimeterofvariousshapes:"); 
		System.out.println("\nRectangle: Length-10, Width-12"); 
		System.out.println("Area: " + rectangle.getArea()); 
		System.out.println("Perimeter: " + rectangle.getPerimeter());
		System.out.println("\nCircle: Radius-5");
		System.out.println("Area: " + circle.getArea());
		System.out.println("Perimeter:"+circle.getPerimeter());
		System.out.println("\nTriangle:Side1-7,Side2-8,Side3-6"); 
		System.out.println("Area: " + triangle.getArea()); 
		System.out.println("Perimeter: " + triangle.getPerimeter());

	}
}

