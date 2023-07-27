class SimpleCalculator {

    private static String s = "Sum: ", d = "Difference: ", p = "Product: ";
    private static int x = 19, y = 10;

    public static int add(int a, int b) {
        return a + b;
    }
    
    public static int subtract(int a, int b) {
        return a - b;
    }
    
    public static int multiply(int a, int b) {
        return a * b;
    }

    public static void main(String[] args) {
        System.out.println(args[0]);
        System.out.print("x = ");
        System.out.println(x);
        System.out.print("y = ");
        System.out.println(y);
        System.out.print(s);
        int sum = add(x, y);
        System.out.println(sum);
        System.out.print(d);
        int difference = subtract(x, y);
        System.out.println(difference);
        System.out.print(p);
        int product = multiply(x, y);
        System.out.println(product);
    }
}