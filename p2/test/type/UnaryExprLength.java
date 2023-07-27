// Type violation in line 6
// .length expression on line 6 expects lvalue expression on line 6 to be an array type. But got 'int'

class Test {
    private static int[] a = new int[5];
    private static int b = a[0].length;
    public static void main(String[] args) {}
}
