class Factorial {
    public static int factorial(int x) {
        if(x == 1 || x == 0) {
            return 1;
        } else {
            return x * factorial(x - 1);
        }
        return 1;
    }

    public static void main(String [ ] args) {
        System.out.println(args[0]);
        int a = factorial(5);
        System.out.println(a);
    }
}