// Type violation in line 6
// Method call expression on line 6 called method 'method' with 1 arguments
// But 'method' declared on line 7 expected to have 2 arguments

class Test {
    private static int a = method(1);
    public static int method(int one, int two) {}
    public static void main(String[] args) {}
}
