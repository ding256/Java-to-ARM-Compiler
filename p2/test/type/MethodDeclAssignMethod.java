// Type violation in line 5
// Expression starting on line 5 evaluated to have type 'int()'. But variable 'a' was declared with type 'int' on line 5

class Test {
    private static int a = method;
    public static int method() {}
    public static void main(String[] args) {}
}
