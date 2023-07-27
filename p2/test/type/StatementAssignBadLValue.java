// Type violation in line 7
// Cannot assign to method type

class Test {
    public static String a() {}
    public static void main(String[] args) {
        a = a;
    }
}
