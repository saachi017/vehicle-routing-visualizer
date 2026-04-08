import React, { useEffect, useState } from "react";
import GraphView from "./components/GraphView";
import ResultsPanel from "./components/ResultsPanel";
import Charts from "./components/Charts";
import "./style/theme.css";

function App() {
  const [data, setData] = useState(null);
  const [selectedAlgo, setSelectedAlgo] = useState("");
  const [dataset, setDataset] = useState("case1");
  const [error, setError] = useState(null);

  useEffect(() => {
    setData(null);
    setError(null);
    fetch(`/${dataset}.json`)
      .then(res => {
        if (!res.ok) throw new Error(`Failed to load ${dataset}.json`);
        return res.json();
      })
      .then(data => {
        setData(data);
        setSelectedAlgo(data.best);
      })
      .catch(err => setError(err.message));
  }, [dataset]);

  if (error) return <p>Error loading data: {error}</p>;
  if (!data) return <p>Loading...</p>;

  return (
    <div className="app">
      <h1 className="title">Vehicle Routing Visualizer</h1>

      <div className="controls-container">
        {/* Dataset Selector */}
        <select
          value={dataset}
          onChange={(e) => setDataset(e.target.value)}
        >
          <option value="case1">Case 1: Standard Instance</option>
          <option value="case2">Case 2: Tight Cluster</option>
          <option value="case3">Case 3: Wide Layout</option>
        </select>

        {/* Algorithm Selector */}
        <select
          value={selectedAlgo}
          onChange={(e) => setSelectedAlgo(e.target.value)}
        >
          {Object.keys(data.results).map(algo => (
            <option key={algo}>{algo}</option>
          ))}
        </select>
      </div>

      <div className="top-section">
        <ResultsPanel data={data} />
        <GraphView data={data} selectedAlgo={selectedAlgo} />
      </div>

      <Charts data={data} />
    </div>
  );
}

export default App;