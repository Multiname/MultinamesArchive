function Calculate(e) {
    let c = document.inputData.polynomial.value.split(" ");
    let l = c.length;

    let a = document.inputData.start.value;
    let b = document.inputData.end.value;
    let n = document.inputData.segments.value;
    let h = (b - a) / n;

    let rect = 0;
    let trap = 0;
    for (let x = a; x < b; x = Number(x) + Number(h)) {
        let y = 0;
        for (let i = 0; i < l; ++i) {
            y += c[i] * Math.pow(Number(x) + h / 2, i);
        }
        rect += y * h;

        let y_0 = 0;
        for (let i = 0; i < l; ++i) {
            y_0 += c[i] * Math.pow(x, i);
        }
        let y_1 = 0;
        for (let i = 0; i < l; ++i) {
            y_0 += c[i] * Math.pow(Number(x) + h, i);
        }
        trap += (Number(y_0) + Number(y_1)) * h / 2;
    }

    document.getElementById("rectangle").innerHTML = 'Метод средних прямоугольников:' + rect;
    document.getElementById("trapezoid").innerHTML = 'Метод трапеций: ' + trap;

    alert('Метод средних прямоугольников:' + rect + '\nМетод трапеций: ' + trap);
}

document.inputData.calculate.addEventListener("click", Calculate);