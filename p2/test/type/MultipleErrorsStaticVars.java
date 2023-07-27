// Type violation in line 8
// Type violation in line 9
// 
// [8] Expression starting on line 8 evaluated to have type 'boolean'. But variable 'a' was declared with type 'int' on line 8
// [9] Expression starting on line 9 evaluated to have type 'String'. But variable 'b' was declared with type 'int' on line 9

class Test {
    private static int a = true;
    private static int b = "Hello";

    public static void main(String[] args) {}
}
