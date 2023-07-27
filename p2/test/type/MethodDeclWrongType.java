// Type violation in line 5
// Expected argument 1 of method invocation of 'method' on line 5 to be of type 'int' but found 'boolean'

class Test {
    private static int a = method(true);
    public static int method(int b) {}
    public static void main(String[] args) {}
}
