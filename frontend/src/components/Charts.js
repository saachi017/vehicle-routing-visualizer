import React from "react";
import { Bar } from "react-chartjs-2";
import {
  Chart as ChartJS,
  BarElement,
  CategoryScale,
  LinearScale,
  Tooltip,
  Legend
} from "chart.js";

ChartJS.register(BarElement, CategoryScale, LinearScale, Tooltip, Legend);

function Charts({ data }) {
  if (!data || !data.results) return <p>No chart data</p>;

  const labels = Object.keys(data.results);

  const distances = labels.map(label => data.results[label].distance);
  const times = labels.map(label => data.results[label].time);

  const chartData = {
    labels: labels,
    datasets: [
      {
        label: "Distance",
        data: distances,
        backgroundColor: "#38bdf8" // blue
      },
      {
        label: "Execution Time (ms)",
        data: times,
        backgroundColor: "#f59e0b" // amber
      }
    ]
  };

  const options = {
    responsive: true,
    plugins: {
      legend: {
        labels: {
          color: "#e2e8f0"
        }
      }
    },
    scales: {
      x: {
        ticks: {
          color: "#e2e8f0"
        },
        grid: {
          color: "#334155"
        }
      },
      y: {
        ticks: {
          color: "#e2e8f0"
        },
        grid: {
          color: "#334155"
        }
      }
    }
  };

  return (
    <div className="card">
      <h3>Algorithm Comparison</h3>
      <Bar data={chartData} options={options} />
    </div>
  );
}

export default Charts;