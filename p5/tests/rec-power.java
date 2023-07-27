class Power {
    public static int power(int base, int exponent) {
        if (exponent == 0) return 1;
        else return base * power(base, exponent - 1);
    }

    public static void main(String[] args) {
        int base = Integer.parseInt(args[0]);
        int exponent = Integer.parseInt(args[1]);
        System.out.println(power(base, exponent));
    }
}
