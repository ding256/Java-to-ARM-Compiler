// Type violation in line 14
// Type violation in line 15
// Type violation in line 16
// Type violation in line 17
// Type violation in line 18
// 
// [14] Expression starting on line 14 evaluated to have type 'boolean'. But variable 'a' was declared with type 'int' on line 14
// [15] Expression starting on line 15 evaluated to have type 'String'. But variable 'b' was declared with type 'int' on line 15
// [16] Symbol 'a' was already declared on line 14 in scope 'Test' with type 'int'
// [17] Symbol 'a' was already declared on line 14 in scope 'Test' with type 'int'
// [18] Symbol 'a' was already declared on line 14 in scope 'Test' with type 'int'

class Test {
    private static int a = true;
    private static int b = "Hello";
    private static int a = 1;
    private static int a = 2;
    private static int a = 2;

    public static void main(String[] args) {}
}

