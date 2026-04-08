import React from "react";

function GraphView({ data, selectedAlgo }) {
  if (!data) return null;

  const route = data.routes[selectedAlgo];

  const width = 500;
  const height = 500;

  const minX = Math.min(...data.nodes.map(n => n.x));
  const maxX = Math.max(...data.nodes.map(n => n.x));
  const minY = Math.min(...data.nodes.map(n => n.y));
  const maxY = Math.max(...data.nodes.map(n => n.y));

  const rangeX = maxX - minX || 1;
  const rangeY = maxY - minY || 1;

  const scaleX = x => ((x - minX) / rangeX) * 400 + 50;
  const scaleY = y => ((y - minY) / rangeY) * 400 + 50;

  const pathString = route.map((nodeId, i) => {
    const node = data.nodes.find(n => n.id === nodeId) || data.nodes[nodeId];
    return `${i === 0 ? 'M' : 'L'} ${scaleX(node.x)},${scaleY(node.y)}`;
  }).join(' ');

  return (
    <div className="card">
      <h3>Route Visualization ({selectedAlgo})</h3>

      <svg width={width} height={height}>
        {/* Edges */}
        {route.map((nodeId, i) => {
          if (i === route.length - 1) return null;

          const from = data.nodes[nodeId];
          const to = data.nodes[route[i + 1]];

          return (
            <line
              key={`${selectedAlgo}-${i}`}
              x1={scaleX(from.x)}
              y1={scaleY(from.y)}
              x2={scaleX(to.x)}
              y2={scaleY(to.y)}
              stroke="#38bdf8"
              strokeWidth="2"
              style={{
                strokeDasharray: 1000,
                strokeDashoffset: 1000,
                animation: "draw 1.2s ease forwards"
              }}
            />
          );
        })}

        {/* Nodes */}
        {data.nodes.map(node => (
          <g key={node.id}>
            <circle
              cx={scaleX(node.x)}
              cy={scaleY(node.y)}
              r="6"
              fill={node.id === 0 ? "#ef4444" : "#f8fafc"}
            />
            <text
              x={scaleX(node.x) + 6}
              y={scaleY(node.y) - 6}
              fontSize="10"
              fill="white"
            >
              {node.id}
            </text>
          </g>
        ))}

        {/* Traveling Vehicle */}
        <g key={`vehicle-${selectedAlgo}`}>
          <circle r="8" fill="#f59e0b" style={{ filter: "drop-shadow(0px 0px 4px #f59e0b)" }} />
          <animateMotion 
            dur="4s" 
            repeatCount="indefinite"
            path={pathString}
          />
        </g>
      </svg>
    </div>
  );
}

export default GraphView;