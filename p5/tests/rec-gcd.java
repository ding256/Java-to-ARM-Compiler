class GCD {
    public static int gcd(int a, int b) {
        if (a == b) {
            return a;
        }
        else if (a > b) {
            return gcd(a - b, b);
        } else {
            return gcd(a, b - a);
        }
    }

    public static void main(String[] args) {
        int a = Integer.parseInt(args[0]);
        int b = Integer.parseInt(args[1]);
        System.out.println(gcd(a, b));
    }
}
