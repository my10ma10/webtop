console.log("APP LOADED");
const cpuEl = document.getElementById("cpu-usage");
const memEl = document.getElementById("memory-usage");
const processTableBody = document.getElementById("process-table-body");

window.onBackendMessage = function(data) {
    updateSystem(data);
    updateProcesses(data);
};

function updateSystem(data) {
    if (data.cpu && typeof data.cpu.total_usage_percent === "number") {
        cpuEl.textContent = data.cpu.total_usage_percent.toFixed(1) + "%";
    }
    if (data.memory) {
        memEl.textContent = (data.memory.used_kb ?? 0) + " / " + (data.memory.total_kb ?? 0) + " KB";
    }
}

function updateProcesses(data) {    
    if (!Array.isArray(data.processes)) return;

    processTableBody.innerHTML = "";
    const fragment = document.createDocumentFragment();

    for (const p of data.processes) {
        const row = document.createElement("tr");

        const cpu = typeof p.cpu_usage?.total_usage_percent === "number" 
            ? p.cpu_usage.total_usage_percent 
            : (typeof p.cpu_percent === "number" ? p.cpu_percent : 0);
            
        const mem = typeof p.res_kb === "number" ? p.res_kb : 0;
        const pid = p.pid ?? p.PID ?? "-";
        const user = p.user ?? p.User ?? "-";
        const name = p.command ?? p.name ?? p.Command ?? "-";
        const state = p.state ?? p.State ?? "-";

        row.innerHTML = `
            <td>${p.pid ?? "-"}</td>
            <td>${p.user ?? "-"}</td>
            <td class="process-name">${name}</td> 
            <td>${cpu.toFixed(1)}</td>
            <td>${mem} KB</td>
            <td>${state ?? "-"}</td>
        `;

        fragment.appendChild(row);
    }

    processTableBody.appendChild(fragment);
}

function callWithRetry(funcName, maxRetries = 20, delayMs = 100, attempt = 1) {
    try {
        if (typeof webui === "undefined" ||
            typeof webui.call !== "function") {
            throw new Error("WebUI not ready");
        }

        if (typeof webui.isConnected === "function" &&
            !webui.isConnected()) {
            throw new Error("WebSocket not connected");
        }

        console.log(`Calling ${funcName} (attempt ${attempt})`);

        webui.call(funcName);

        return;

    } 
    catch (err) {

        const isRetryable =
            err.message.includes("WebSocket") ||
            err.message.includes("not connected") ||
            err.message.includes("not ready");

        if (isRetryable && attempt < maxRetries) {

            console.log(`Retry ${attempt}/${maxRetries}`);

            setTimeout(() => {
                callWithRetry(funcName, maxRetries, delayMs, attempt + 1);
            }, delayMs);

            return;
        }

        console.error(`Failed to call ${funcName}`, err);
    }
}

function initApp() {
    console.log("WebUI bridge initialized");
    callWithRetry("frontend_ready");
}

function waitForWebUI(maxAttempts = 100) {
    let attempts = 0;
    
    const check = () => {
        attempts++;
        
        if (typeof webui !== 'undefined' && typeof webui.call === 'function') {
            console.log("webui object ready after", attempts * 50, "ms");
            
            initApp();
            return;
        }
        
        if (attempts >= maxAttempts) {
            console.error("Timeout: webui object not available");
            return;
        }
        
        setTimeout(check, 50);
    };
    
    check();
}

waitForWebUI();