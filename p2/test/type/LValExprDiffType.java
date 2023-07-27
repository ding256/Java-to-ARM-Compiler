// Type violation in line 6
// Expression starting on line 6 evaluated to have type 'int'. But variable 'b' was declared with type 'boolean' on line 6

class Test {
    private static int[] arr = new int[5];
    private static boolean b = arr[1];
    public static void main(String[] args) {}
}
