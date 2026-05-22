const cpuUsageElement = document.getElementById("cpu-usage");
const memoryUsageElement = document.getElementById("memory-usage");

const processTableBody = document.getElementById(
    "process-table-body"
);

/**
 * Вызывается мостом на бэкенде
 */
window.onBackendMessage = function (data) {
    console.log("MESSAGE RECEIVED");
    
    console.log("Received:", data);

    updateSystem(data);
    updateProcesses(data.processes);
};

function updateSystem(data) {

    if (data.cpu) {
        cpuUsageElement.textContent =
            `${data.cpu.total_usage.toFixed(1)}%`;
    }

    if (data.memory) {

        const used = data.memory.used_mb;
        const total = data.memory.total_mb;

        memoryUsageElement.textContent =
            `${used} / ${total} MB`;
    }
}

function updateProcesses(processes) {

    processTableBody.innerHTML = "";

    for (const process of processes) {

        const row = document.createElement("tr");

        row.innerHTML = `
            <td>${process.pid}</td>
            <td>${process.user}</td>
            <td class="process-name">${process.name}</td>
            <td>${process.cpu_usage.toFixed(1)}</td>
            <td>${process.memory_kb} KB</td>
            <td class="process-state">${process.state}</td>
        `;

        processTableBody.appendChild(row);
    }
}