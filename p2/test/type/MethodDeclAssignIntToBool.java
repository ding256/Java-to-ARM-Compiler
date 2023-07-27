// Type Violation in Line 5
// Expression starting on line 5 evaluated to have type 'int'. But variable 'a' was declared with type 'boolean' on line 5

class Test {
    private static boolean a = method();
    public static int method() {}
    public static void main(String[] args) {}
}
