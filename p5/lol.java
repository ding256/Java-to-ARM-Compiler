class Test {
    private static String hello = "sfjei_ l&63_ )!@#:$%''^&*(` 24:^453|}{[;',./<>?']}\"\"";
    private static int d = 4;
    public static int method1(int a) {
        a = a + 1;
        return a;
    }
    public static int method2(int a, int b, int c, int d) {
        a = method1(a);
        d = method1(b) + method1(c);
        int x = 3 * 2;
        int y = method1(2) * 1;
        int z = 1 * method1(2);
        System.out.println(x);
        System.out.println(y);
        System.out.println(z);
        System.out.println(3 * 2);
        System.out.println(method1(2) * 1);
        System.out.println(1 * method1(2));
        System.out.println(method1(2) * method1(2));
        System.out.println(a * d);
        System.out.println(method1(d));
        return d;
    }
    public static void main(String[] args) {
        System.out.println(args[0]);
        System.out.println(123);
        int a = 3 + 4;
        System.out.println(a);
        int b = (a + 2) * 3;
        System.out.println(b);
        int c = a + d;
        c = c + 1;
        System.out.println(c);
        System.out.println(a * (b + c) + method2(a, (4 + method1(2)) * d, c, method1(b)) - c * (d - 150) + method1(a));
        System.out.println(hello);
        System.out.println("\f\t\'\"?_ ):");
        System.out.println(d);
        int e = -(a + d);
        e = -method1(a + d - 1);
        e = -(method1(a + d - 1) + d - a);
        int f = +(b);
        System.out.println(e);
        System.out.println(f);
        a = 2;
        b = c + a;
        c = -(c);
        System.out.println(a);
        System.out.println(b);
        System.out.println(c);
        int test = method1(3);
        System.out.println(test);
        method2(1, d, method1(2), a);
    }
}
