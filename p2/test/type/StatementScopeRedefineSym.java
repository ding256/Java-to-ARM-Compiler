// Type violation in line 9
// Symbol 'a' was already declared on line 7 in scope '{} statement on line 6' with type 'int'

class Test {
    public static void main(String[] args) {
        {
            int a;
            {
                int a;
            }
        }
    }
}
