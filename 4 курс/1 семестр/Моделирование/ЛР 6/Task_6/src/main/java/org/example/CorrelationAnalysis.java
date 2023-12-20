package org.example;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;

import javax.swing.*;

public class CorrelationAnalysis extends JFrame {

    private static final int N = 100; // Размер выборки
    private static double[] data = new double[N]; // Ваши данные

    // Функция для расчета нормированной корреляционной функции
    private static double normalizedCorrelationFunction(int z) {
        double sum = 0;

        for (int i = 0; i < N - z; ++i) {
            sum += (data[i] * data[i + z]);
        }

        double mean = 0;
        for (double datum : data) {
            mean += datum;
        }
        mean /= N;

        double variance = 0;
        for (double datum : data) {
            variance += (datum - mean) * (datum - mean);
        }

        return sum / Math.sqrt(variance * variance);
    }

    // Функция для построения графика
    private void plotGraph(XYSeries series) {
        XYSeriesCollection dataset = new XYSeriesCollection(series);
        JFreeChart chart = ChartFactory.createXYLineChart(
                "Нормированная автокорреляционная функция",
                "Z",
                "Rn",
                dataset,
                PlotOrientation.VERTICAL,
                true,
                true,
                false
        );

        ChartPanel chartPanel = new ChartPanel(chart);
        chartPanel.setPreferredSize(new java.awt.Dimension(560, 370));
        setContentPane(chartPanel);

        pack();
        setLocationRelativeTo(null);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
    }

    public static void main(String[] args) {
        CorrelationAnalysis correlationAnalysis = new CorrelationAnalysis();

        // Замените data на ваши реальные данные
        for (int i = 0; i < N; ++i) {
            data[i] = Math.random() * 1000; // Пример случайных данных
        }

        // 1. Расчет нормированной корреляционной функции для интервального сдвига z от 0 до 50
        XYSeries series = new XYSeries("Нормированная автокорреляционная функция");

        for (int z = 0; z <= 50; ++z) {
            double result = correlationAnalysis.normalizedCorrelationFunction(z);
            series.add(z, result);
        }

        // 2. Построение графика нормированной автокорреляционной функции
        correlationAnalysis.plotGraph(series);

        // 3. Расчет нормированной корреляционной функции для объема выборки N = 410
        int N_new = 740;
        System.out.printf("Нормированная корреляционная функция при выборке N = %d: %f\n", N_new, correlationAnalysis.normalizedCorrelationFunction(0));
    }
}
