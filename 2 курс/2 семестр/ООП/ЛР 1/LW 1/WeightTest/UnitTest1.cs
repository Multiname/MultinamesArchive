using Microsoft.VisualStudio.TestTools.UnitTesting;
using LW_1;

namespace WeightTest
{
    [TestClass]
    public class WeightTest
    {
        [TestMethod]
        public void TestCreateFromGrams()
        {
            Assert.AreEqual(50.4f, Weight.CreateFromGrams(50.4f).Grams);
        }
        [TestMethod]
        public void TestCreateFromPounds()
        {
            Assert.AreEqual(2.3f, Weight.CreateFromPounds(2.3f).Pounds);
        }
        [TestMethod]
        public void TestGrams()
        {
            Weight weight = Weight.CreateFromGrams(0);
            weight.Grams = 1.5f;
            Assert.AreEqual(1.5f, weight.Grams);
        }
        [TestMethod]
        public void TestPounds()
        {
            Weight weight = Weight.CreateFromGrams(0);
            weight.Pounds = 12.42f;
            Assert.AreEqual(12.42f, weight.Pounds);
        }
        [TestMethod]
        public void TestOunces()
        {
            Weight weight = Weight.CreateFromGrams(0);
            weight.Ounces = 65.3f;
            Assert.AreEqual(65.3f, weight.Ounces);
        }
        [TestMethod]
        public void TestAddition()
        {
            Weight weight_1 = Weight.CreateFromGrams(4.2f);
            Weight weight_2 = Weight.CreateFromGrams(5.5f);
            Assert.AreEqual(9.7f, (weight_1 + weight_2).Grams);
        }
        [TestMethod]
        public void TestSubtraction()
        {
            Weight weight_1 = Weight.CreateFromGrams(20.5f);
            Weight weight_2 = Weight.CreateFromGrams(12.2f);
            Assert.AreEqual(8.3f, (weight_1 - weight_2).Grams);
        }
    }
}
