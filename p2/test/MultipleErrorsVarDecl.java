// Type violation in line 19
// Type violation in line 20
// Type violation in line 21
// Type violation in line 21
// Type violation in line 21
// 
// [19] Expression starting on line 19 evaluated to have type 'boolean'. But variable 'a' was declared with type 'int' on line 19
// [20] Symbol 'a' was already declared on line 19 in scope 'main' with type 'int'
// [21] Binary operator '+' expects both left and right to be the same.
// left expression on line 21 was of type 'String'
// right expression on line 21 was of type 'int'
// [21] Method call expression on line 21 called method 's' with 2 arguments
// But 's' declared on line 17 expected to have 1 arguments
// [21] Expected argument 1 of method invocation of 's' on line 21 to be of type 'int' but found 'boolean'

class Test {
    public static String s(int a) {}
    public static void main(String[] args) {
        int a = true;
        String a = "hello";
        boolean b = s(false, "extra arg" + 1);
    }
}
