// Type violation in line 9
// Type violation in line 10
// 
// [9] Symbol 'a' was already declared on line 8 in scope 'Test' with type 'int'
// [10] Symbol 'a' was already declared on line 8 in scope 'Test' with type 'int'

class Test {
    private static int a = 1;
    private static int a = 2;
    private static int a = 2;

    public static void main(String[] args) {}
}
