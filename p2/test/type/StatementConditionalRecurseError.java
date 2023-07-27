// Type violation in line 7
// Expression starting on line 7 evaluated to have type 'String'. But variable 'a' was declared with type 'int' on line 7

class Test {
    public static void main(String[] args) {
        if (true) {
            int a = "hello";
        } else {}
    }
}
