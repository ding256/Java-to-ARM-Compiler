// Type violation in line 6
// Too many bracket expressions 2 for type 'int[]' with arrayDegrees of 1

class Test {
    private static int[] a = new int[5];
    private static int b = a[1][2];
    public static void main(String[] args) {}
}
