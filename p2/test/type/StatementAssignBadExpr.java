// Type violation in line 9
// 
// [9] Binary operator '+' expects both left and right to be the same.
// left expression on line 9 was of type 'boolean'
// right expression on line 9 was of type 'String'

class Test {
    public static void main(String[] args) {
        args = true + "false";
    }
}
