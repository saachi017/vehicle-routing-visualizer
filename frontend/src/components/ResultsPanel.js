import React from "react";

function ResultsPanel({ data }) {
  return (
    <div className="card highlight">
      <h2>🏆 Best: {data.best}</h2>

      {Object.entries(data.results).map(([algo, val]) => (
        <div key={algo}>
          <strong>{algo}</strong><br />
          Distance: {val.distance.toFixed(2)} <br />
          Time: {val.time.toFixed(2)} ms
        </div>
      ))}
    </div>
  );
}

export default ResultsPanel;