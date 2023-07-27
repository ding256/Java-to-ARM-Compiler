// Type violation in line 5
// Expression starting on line 5 evaluated to have type 'int'. But variable 's' was declared with type 'String' on line 5

class Test {
    private static String s = method();
    public static int method() {}
    public static void main(String[] args) {}
}
