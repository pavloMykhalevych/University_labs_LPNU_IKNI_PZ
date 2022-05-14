import React  from "react";
import { Bar } from "react-chartjs-2";
import {
  Chart as ChartJS,
  CategoryScale,
  LinearScale,
  BarElement,
  Title,
  Tooltip,
  Legend,
} from 'chart.js';

ChartJS.register(
  CategoryScale,
  LinearScale,
  BarElement,
  Title,
  Tooltip,
  Legend
);

const labels = ["wk", "wp", "wb", "bk", "bb"];

export const data = {
  labels,
  datasets: [
    {
      label: 'Chesses',
      data: [1,2,3,4,5],
      backgroundColor: ["white", "white","white","black","black"],
    },
  ],
};

function ChartField() {
  return (
    <div className="ChartField">
        <Bar data={data} options={{maintainAspectRatio: false}} width={400} height={300}/>
    </div>
  );
}

export default ChartField;
