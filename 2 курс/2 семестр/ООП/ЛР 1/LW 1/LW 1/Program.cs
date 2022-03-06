namespace LW_1
{
    public class Weight
    {
        private const float GramsInPound = 453.59237f;
        private const float GramsInOunce = 28.349523125f;
        
        private float _grams;

        private Weight(float grams) { _grams = grams; }
        public static Weight CreateFromGrams(float grams) {
            return new Weight(grams);
        }
        public static Weight CreateFromPounds(float pounds) {
            return new Weight(pounds * GramsInPound);
        }

        public float Grams
        {
            get { return _grams; }
            set { _grams = value; }
        }
        public float Pounds
        {
            get { return _grams / GramsInPound; }
            set { _grams = value * GramsInPound; }
        }
        public float Ounces
        {
            get { return _grams / GramsInOunce; }
            set { _grams = value * GramsInOunce; }
        }

        public static Weight operator+(Weight weight_1, Weight weight_2) {
            return CreateFromGrams(weight_1.Grams + weight_2.Grams);
        }
        public static Weight operator-(Weight weight_1, Weight weight_2) {
            return CreateFromGrams(weight_1.Grams - weight_2.Grams);
        }
    }

    public class LW_1
    {
        public static void Main() {}
    }
}
