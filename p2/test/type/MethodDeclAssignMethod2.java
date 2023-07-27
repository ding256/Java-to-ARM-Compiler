// Type violation in line 5
// Expression starting on line 5 evaluated to have type 'boolean(int)'. But variable 'b' was declared with type 'boolean' on line 5

class Test {
    private static boolean b = method;
    public static boolean method(int a) {}
    public static void main(String[] args) {}
}
