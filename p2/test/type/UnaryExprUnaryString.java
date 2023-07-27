// Type violation in line 5
// Unary operator '+' expects operand to be of type 'int' but found expression starting on line 5 to be of type 'String'

class Test {
    private static int a = +"Hello";
    public static void main(String[] args) {}
}
