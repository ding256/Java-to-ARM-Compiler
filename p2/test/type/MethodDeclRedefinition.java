// Type violation in line 6
// Symbol 'a' was already declared on line 5 in scope 'Test' with type 'int()'

class Test {
    public static int a() {}
    public static int a() {}

    public static void main(String[] args) {}
}
