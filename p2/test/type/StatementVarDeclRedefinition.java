// Type violation in line 7
// Symbol 'a' was already declared on line 6 in scope 'main' with type 'int'

class Test {
    public static void main(String[] args) {
        int a = 1;
        String a = "hello";
    }
}
