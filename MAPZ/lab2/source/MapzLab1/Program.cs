using System;
using System.Diagnostics;

namespace MapzLab1
{
    // First task
    /*abstract class MyAbstractClass
    {
        public abstract void AbstractMethod();
    }

    interface MyInterface
    {
        void InterfaceMethod();
    }

    class MyClass: MyAbstractClass, MyInterface
    {
        void MyInterface.InterfaceMethod()
        {
            throw new NotImplementedException();
        }

        public override void AbstractMethod()
        {
            throw new NotImplementedException();
        }
    }*/
    // Second task
    /*
    class BaseClass
    {
        private int privateInt;
        protected int protectedInt;
        public int publicInt;
        public BaseClass()
        {

        }
    }

    class FirstClass
    {
        public FirstClass()
        {
            BaseClass bc = new BaseClass();
            bc.publicInt = 5;
            bc.protectedInt = 5;
            bc.privateInt = 5;
        }
    }
    class SecondClass : BaseClass
    {
        public SecondClass()
        {
            publicInt = 5;
            protectedInt = 5;
            privateInt = 5;
        }
    }*/
    //Third and 4 task
    /*class BaseClass
    {
        public int publicInt;
        public BaseClass()
        {

        }

        int myInt;

        class MyClass
        {

        }
    }

    struct MyStruct
    {

    }


    class FirstClass
    {
        public FirstClass()
        {
            BaseClass bc = new BaseClass();
            MyStruct str = new MyStruct();
            bc.myInt = 3;
            BaseClass.MyClass;
        }
    }*/
    //5 task
    /*enum Food
    {
        Apple,
        Banana,
        Orange,
        Potato,
        Cherry,
        Tomato,
        Cucumber,
        Fruits = Apple | Banana | Orange | Cherry,
        Vegetables = Potato | Tomato | Cucumber
    }

    class Program
    {
        static void Main(string[] args)
        {
            bool isCherryFruit = (Food.Fruits & Food.Cherry) == Food.Cherry;
            if (isCherryFruit)
            {
                Console.WriteLine("Cherry is fruit");
            }
            bool isPotatoVEgetable = (Food.Vegetables & Food.Potato) == Food.Potato;
            if (isPotatoVEgetable)
            {
                Console.WriteLine("Potato is vegetable");
            }
        }
    }*/
    //6 task
    /*abstract class MyAbstractClass
    {
        public abstract void AbstractMethod();
    }

    interface MyInterface
    {
        void InterfaceMethod();
    }

    interface MyInterface2
    {
        void SecondInterfaceMethod();
    }

    class MyClass : MyAbstractClass, MyInterface, MyInterface2
    {
        void MyInterface.InterfaceMethod()
        {
            throw new NotImplementedException();
        }
        void MyInterface2.SecondInterfaceMethod()
        {
            throw new NotImplementedException();
        }

        public override void AbstractMethod()
        {
            throw new NotImplementedException();
        }
    }*/
    //7 task
    /*class BaseClass
    {
        public int publicInt;
        public BaseClass()
        {
            publicInt = 3;
        }
    }

    class Class : BaseClass
    {
        public int myInt;
        public Class() : base()
        {
            myInt = 4;
        }

        public Class(int n) : this()
        {
            myInt = n;
        }

        static void Main(string[] args)
        {
            Class myClass = new Class();
            Console.WriteLine("Base class int = {0}\nDerived class int = {1}", myClass.publicInt, myClass.myInt);
        }
    }*/
    //8 task
    /* class MyClass
     {
         // Static variable
         static int s;

         // Non-static variable
         int ns;

         // Declaration of
         // static constructor
         static MyClass()
         {
             s = 1;
             Console.WriteLine("It is static constructor");
         }

         // Declaration of
         // non-static constructor
         public MyClass()
         {
             ns = 2;
             Console.WriteLine("It is non-static constructor");
         }

         static void Main(string[] args)
         {
             MyClass obj1 = new MyClass();
             MyClass obj2 = new MyClass();
         }
     }*/
    //9 task
    /*class MyClass
    {
        public void set4(int value)
        {
            value = 4;
        }

        public void set5(ref int value)
        {
            value = 5;
        }
        public void set6(out int value)
        {
            value = 6;
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            int a = 1, b = 2, c;

            MyClass SC = new MyClass();

            SC.set4(a);
            SC.set5(ref b);
            SC.set6(out c);

            Console.WriteLine($"{a} {b} {c}");
        }
    }*/

    //10 task
    /* class Program
     {
         static void Main(string[] args)
         {
             int i = 123;      // a value type
             object o = i;     // boxing
             int j = (int)o;   // unboxing

             Console.WriteLine($"i = {i} \no = {o} \nj = {j}");
         }
     }*/
    //11 task
    /*public class Role
    {
        public string Name { get; set; }

        public static explicit operator Role(string roleName)
        {
            return new Role() { Name = roleName };
        }

        static void Main(string[] args)
        {
            Role role = (Role)"RoleName";

            Console.WriteLine($"Name = {role.Name}");
        }

    }*/
    //12 task

    /*class Class4
    {
        public int a1;
        public int a2;
        public int a3;
        public int a4;

        public Class4()
        {
            a1 = 1;
            a2 = 2;
            a3 = 3;
            a4 = 4;
        }
    }

    class Class3
    {
        public int b1;
        public int b2;
        public int b3;
        public Class3()
        {
            b1 = 5;
            b2 = 6;
            b3 = 7;
        }
    }

    class Class2
    {
        public int c1;
        public int c2;
        public Class2()
        {
            c1 = 8;
            c2 = 9;
        }
    }

    class Class1
    {
        public int d;
        public Class1()
        {
            d = 0;
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Using ten milions operations for classes.");
            Stopwatch sw = new Stopwatch();
            sw.Start();
            Class1 a = new Class1();
            for (int m = 1; m < 10000000; ++m)
            {
                Class1 a1 = new Class1();
            }
            sw.Stop();
            Console.WriteLine("Class1 assign: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            object _a = (object)a;
            for (int m = 1; m < 10000000; ++m)
            {

                object __a = (object)a;
            }
            sw.Stop();
            Console.WriteLine("Class1 boxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            for (int m = 0; m < 10000000; ++m)
            {
                Class1 a2 = (Class1)_a;
            }
            sw.Stop();
            Console.WriteLine("Class1 unboxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            //Class2
            sw.Restart();
            Class2 b = new Class2();
            for (int m = 1; m < 10000000; ++m)
            {
                Class2 b1 = new Class2();
            }
            sw.Stop();
            Console.WriteLine("Class2 assign: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            object _b = (object)b;
            for (int m = 1; m < 10000000; ++m)
            {

                object __b = (object)b;
            }
            sw.Stop();
            Console.WriteLine("Class2 boxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            for (int m = 0; m < 10000000; ++m)
            {
                Class2 b2 = (Class2)_b;
            }
            sw.Stop();
            Console.WriteLine("Class2 unboxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            //Class3
            sw.Restart();
            Class3 c = new Class3();
            for (int m = 1; m < 10000000; ++m)
            {
                Class3 c1 = new Class3();
            }
            sw.Stop();
            Console.WriteLine("Class3 assign: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            object _c = (object)c;
            for (int m = 1; m < 10000000; ++m)
            {

                object __c = (object)c;
            }
            sw.Stop();
            Console.WriteLine("Class3 boxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            for (int m = 0; m < 10000000; ++m)
            {
                Class3 c2 = (Class3)_c;
            }
            sw.Stop();
            Console.WriteLine("Class3 unboxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            //Class4
            sw.Restart();
            Class4 d = new Class4();
            for (int m = 1; m < 10000000; ++m)
            {
                Class4 d1 = new Class4();
            }
            sw.Stop();
            Console.WriteLine("Class4 assign: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            object _d = (object)d;
            for (int m = 1; m < 10000000; ++m)
            {

                object __d = (object)d;
            }
            sw.Stop();
            Console.WriteLine("Class4 boxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            for (int m = 0; m < 10000000; ++m)
            {
                Class4 d2 = (Class4)_d;
            }
            sw.Stop();
            Console.WriteLine("Class4 unboxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            //Types
            Console.WriteLine("Using one bilion operations for types.");
            sw.Restart();
            sw.Start();
            for(int m = 0; m < 1000000000; ++m)
            {
                int myint = 123123123;
            }
            sw.Stop();
            Console.WriteLine("Int assign: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            object _myint = (object)123123123;
            for (int m = 1; m < 1000000000; ++m)
            {
                object __myint = (object)123123123;
            }
            sw.Stop();
            Console.WriteLine("Int boxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            for (int m = 0; m < 1000000000; ++m)
            {
                int myint_ = (int)_myint;
            }
            sw.Stop();
            Console.WriteLine("Int unboxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            for (int m = 0; m < 1000000000; ++m)
            {
                double i = 123123123.123123123123;
            }
            sw.Stop();
            Console.WriteLine("Double assign: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            object o = (object)123123123.123123123123;
            for (int m = 1; m < 1000000000; ++m)
            {
                object _o = (object)123123123.123123123123;
            }
            sw.Stop();
            Console.WriteLine("Double boxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            for (int m = 0; m < 1000000000; ++m)
            {
                double j = (double)o;
            }
            sw.Stop();
            Console.WriteLine("Double unboxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            for (int m = 0; m < 1000000000; ++m)
            {
                float myfloat = 123123123.123123F;
            }
            sw.Stop();
            Console.WriteLine("Float assign: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            object _myfloat = (object)123123123.123123F;
            for (int m = 1; m < 1000000000; ++m)
            {
                object __myfloat = (object)123123123.123123F;
            }
            sw.Stop();
            Console.WriteLine("Float boxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            for (int m = 0; m < 1000000000; ++m)
            {
                float myfloat_ = (float)_myfloat;
            }
            sw.Stop();
            Console.WriteLine("Float unboxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");
        }
    }*/
    //13 task
    /*struct Class4
    {
        public int a1;
        public int a2;
        public int a3;
        public int a4;
    }

    struct Class3
    {
        public int b1;
        public int b2;
        public int b3;
    }

    struct Class2
    {
        public int c1;
        public int c2;
    }

    struct Class1
    {
        public int d;
    }

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Using ten milions operations for classes.");
            Stopwatch sw = new Stopwatch();
            sw.Start();
            Class1 a = new Class1();
            for (int m = 1; m < 10000000; ++m)
            {
                Class1 a1 = new Class1();
            }
            sw.Stop();
            Console.WriteLine("Class1 assign: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            object _a = (object)a;
            for (int m = 1; m < 10000000; ++m)
            {

                object __a = (object)a;
            }
            sw.Stop();
            Console.WriteLine("Class1 boxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            for (int m = 0; m < 10000000; ++m)
            {
                Class1 a2 = (Class1)_a;
            }
            sw.Stop();
            Console.WriteLine("Class1 unboxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            //Class2
            sw.Restart();
            Class2 b = new Class2();
            for (int m = 1; m < 10000000; ++m)
            {
                Class2 b1 = new Class2();
            }
            sw.Stop();
            Console.WriteLine("Class2 assign: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            object _b = (object)b;
            for (int m = 1; m < 10000000; ++m)
            {

                object __b = (object)b;
            }
            sw.Stop();
            Console.WriteLine("Class2 boxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            for (int m = 0; m < 10000000; ++m)
            {
                Class2 b2 = (Class2)_b;
            }
            sw.Stop();
            Console.WriteLine("Class2 unboxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            //Class3
            sw.Restart();
            Class3 c = new Class3();
            for (int m = 1; m < 10000000; ++m)
            {
                Class3 c1 = new Class3();
            }
            sw.Stop();
            Console.WriteLine("Class3 assign: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            object _c = (object)c;
            for (int m = 1; m < 10000000; ++m)
            {

                object __c = (object)c;
            }
            sw.Stop();
            Console.WriteLine("Class3 boxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            for (int m = 0; m < 10000000; ++m)
            {
                Class3 c2 = (Class3)_c;
            }
            sw.Stop();
            Console.WriteLine("Class3 unboxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            //Class4
            sw.Restart();
            Class4 d = new Class4();
            for (int m = 1; m < 10000000; ++m)
            {
                Class4 d1 = new Class4();
            }
            sw.Stop();
            Console.WriteLine("Class4 assign: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            object _d = (object)d;
            for (int m = 1; m < 10000000; ++m)
            {

                object __d = (object)d;
            }
            sw.Stop();
            Console.WriteLine("Class4 boxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            for (int m = 0; m < 10000000; ++m)
            {
                Class4 d2 = (Class4)_d;
            }
            sw.Stop();
            Console.WriteLine("Class4 unboxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            //Types
            Console.WriteLine("Using one bilion operations for types.");
            sw.Restart();
            sw.Start();
            for (int m = 0; m < 1000000000; ++m)
            {
                int myint = 123123123;
            }
            sw.Stop();
            Console.WriteLine("Int assign: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            object _myint = (object)123123123;
            for (int m = 1; m < 1000000000; ++m)
            {
                object __myint = (object)123123123;
            }
            sw.Stop();
            Console.WriteLine("Int boxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            for (int m = 0; m < 1000000000; ++m)
            {
                int myint_ = (int)_myint;
            }
            sw.Stop();
            Console.WriteLine("Int unboxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            for (int m = 0; m < 1000000000; ++m)
            {
                double i = 123123123.123123123123;
            }
            sw.Stop();
            Console.WriteLine("Double assign: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            object o = (object)123123123.123123123123;
            for (int m = 1; m < 1000000000; ++m)
            {
                object _o = (object)123123123.123123123123;
            }
            sw.Stop();
            Console.WriteLine("Double boxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            for (int m = 0; m < 1000000000; ++m)
            {
                double j = (double)o;
            }
            sw.Stop();
            Console.WriteLine("Double unboxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            for (int m = 0; m < 1000000000; ++m)
            {
                float myfloat = 123123123.123123F;
            }
            sw.Stop();
            Console.WriteLine("Float assign: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            object _myfloat = (object)123123123.123123F;
            for (int m = 1; m < 1000000000; ++m)
            {
                object __myfloat = (object)123123123.123123F;
            }
            sw.Stop();
            Console.WriteLine("Float boxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            for (int m = 0; m < 1000000000; ++m)
            {
                float myfloat_ = (float)_myfloat;
            }
            sw.Stop();
            Console.WriteLine("Float unboxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");
        }
    }*/
    //14 task
    /*class Point
    {
        public int x, y;

        public Point(int x, int y)
        {
            this.x = x;
            this.y = y;
        }

        public override bool Equals(object obj)
        {
            if (obj.GetType() != this.GetType()) return false;

            var other = (Point)obj;
            return (this.x == other.x) && (this.y == other.y);
        }

        public override int GetHashCode()
        {
            return x ^ y;
        }

        public override String ToString()
        {
            return $"({x}, {y})";
        }

        static void Main()
        {
            var p1 = new Point(1, 2);

            var p3 = p1;

            Console.WriteLine(Object.Equals(p1, p3));

            Console.WriteLine($"p1's value is: {p1.ToString()}");
        }
    }*/

    //Second part
    struct Class4
    {
        public int a1;
        public int a2;
        public int a3;
        public int a4;
    }

    struct Class3
    {
        public int b1;
        public int b2;
        public int b3;
    }

    struct Class2
    {
        public int c1;
        public int c2;
    }

    struct Class1
    {
        public int d;
    }

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Using ten milions operations for classes.");
            Stopwatch sw = new Stopwatch();
            sw.Start();
            Class1 a = new Class1();
            for (int m = 1; m < 10000000; ++m)
            {
                Class1 a1 = new Class1();
            }
            sw.Stop();
            Console.WriteLine("Class1 assign: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            object _a = (object)a;
            for (int m = 1; m < 10000000; ++m)
            {

                object __a = (object)a;
            }
            sw.Stop();
            Console.WriteLine("Class1 boxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            for (int m = 0; m < 10000000; ++m)
            {
                Class1 a2 = (Class1)_a;
            }
            sw.Stop();
            Console.WriteLine("Class1 unboxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            //Class2
            sw.Restart();
            Class2 b = new Class2();
            for (int m = 1; m < 10000000; ++m)
            {
                Class2 b1 = new Class2();
            }
            sw.Stop();
            Console.WriteLine("Class2 assign: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            object _b = (object)b;
            for (int m = 1; m < 10000000; ++m)
            {

                object __b = (object)b;
            }
            sw.Stop();
            Console.WriteLine("Class2 boxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            for (int m = 0; m < 10000000; ++m)
            {
                Class2 b2 = (Class2)_b;
            }
            sw.Stop();
            Console.WriteLine("Class2 unboxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            //Class3
            sw.Restart();
            Class3 c = new Class3();
            for (int m = 1; m < 10000000; ++m)
            {
                Class3 c1 = new Class3();
            }
            sw.Stop();
            Console.WriteLine("Class3 assign: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            object _c = (object)c;
            for (int m = 1; m < 10000000; ++m)
            {

                object __c = (object)c;
            }
            sw.Stop();
            Console.WriteLine("Class3 boxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            for (int m = 0; m < 10000000; ++m)
            {
                Class3 c2 = (Class3)_c;
            }
            sw.Stop();
            Console.WriteLine("Class3 unboxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            //Class4
            sw.Restart();
            Class4 d = new Class4();
            for (int m = 1; m < 10000000; ++m)
            {
                Class4 d1 = new Class4();
            }
            sw.Stop();
            Console.WriteLine("Class4 assign: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            object _d = (object)d;
            for (int m = 1; m < 10000000; ++m)
            {

                object __d = (object)d;
            }
            sw.Stop();
            Console.WriteLine("Class4 boxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            for (int m = 0; m < 10000000; ++m)
            {
                Class4 d2 = (Class4)_d;
            }
            sw.Stop();
            Console.WriteLine("Class4 unboxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            //Types
            Console.WriteLine("Using one bilion operations for types.");
            sw.Restart();
            sw.Start();
            for (int m = 0; m < 1000000000; ++m)
            {
                int myint = 123123123;
            }
            sw.Stop();
            Console.WriteLine("Int assign: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            object _myint = (object)123123123;
            for (int m = 1; m < 1000000000; ++m)
            {
                object __myint = (object)123123123;
            }
            sw.Stop();
            Console.WriteLine("Int boxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            for (int m = 0; m < 1000000000; ++m)
            {
                int myint_ = (int)_myint;
            }
            sw.Stop();
            Console.WriteLine("Int unboxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            for (int m = 0; m < 1000000000; ++m)
            {
                double i = 123123123.123123123123;
            }
            sw.Stop();
            Console.WriteLine("Double assign: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            object o = (object)123123123.123123123123;
            for (int m = 1; m < 1000000000; ++m)
            {
                object _o = (object)123123123.123123123123;
            }
            sw.Stop();
            Console.WriteLine("Double boxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            for (int m = 0; m < 1000000000; ++m)
            {
                double j = (double)o;
            }
            sw.Stop();
            Console.WriteLine("Double unboxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            for (int m = 0; m < 1000000000; ++m)
            {
                float myfloat = 123123123.123123F;
            }
            sw.Stop();
            Console.WriteLine("Float assign: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            object _myfloat = (object)123123123.123123F;
            for (int m = 1; m < 1000000000; ++m)
            {
                object __myfloat = (object)123123123.123123F;
            }
            sw.Stop();
            Console.WriteLine("Float boxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");

            sw.Restart();
            for (int m = 0; m < 1000000000; ++m)
            {
                float myfloat_ = (float)_myfloat;
            }
            sw.Stop();
            Console.WriteLine("Float unboxing: " + sw.ElapsedMilliseconds.ToString() + "miliseconds");
        }
    }
}
