// Type violation in line 8
// Symbol 'a' was already declared on line 6 in scope 'main' with type 'int'

class Test {
    public static void main(String[] args) {
        int a;
        {
            String a;
        }
    }
}
