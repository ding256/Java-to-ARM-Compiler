// Type Violation in Line 7
// Expected argument 1 of method invocation of 'method' on line 7 to be of type 'int' but found 'boolean'

class Test {
    public static int method(int b) {}
    public static void main(String[] args) {
        method(true);
    }
}
