-- Driver de QA: o mGBA headless fica parado esperando comandos em CMD_FILE.
-- Cada lote de comandos e executado quadro a quadro; ao terminar, escreve ACK_FILE.
-- Comandos (um por linha):
--   press KEY [hold] [after]   aperta KEY por `hold` quadros (6) e espera `after` (20)
--   hold KEY N                 segura KEY por N quadros
--   combo K1+K2 [hold] [after] aperta varias teclas juntas
--   wait N                     espera N quadros
--   shot PATH                  screenshot PNG
--   save PATH / load PATH      savestate
--   r8/r16/r32 ADDR            le memoria (resultado vai para ACK_FILE)
--   range ADDR LEN             le bloco em hex
--   w8/w16/w32 ADDR VAL        escreve memoria
--   quit
local DIR = os.getenv("QA_DIR") or "/tmp/qa"
local CMD_FILE = DIR .. "/cmd.txt"
local ACK_FILE = DIR .. "/ack.txt"

local KEYS = { A = 0, B = 1, SELECT = 2, START = 3, RIGHT = 4, LEFT = 5, UP = 6, DOWN = 7, R = 8, L = 9 }

local queue = {}
local out = {}
local cur = nil     -- acao em andamento {kind, frames, keys}

local function file_exists(p) local f = io.open(p, "r"); if f then f:close(); return true end; return false end

local function keymask(spec)
  local m = 0
  for k in string.gmatch(spec, "[^+]+") do m = m | (1 << KEYS[k]) end
  return m
end

local function load_cmds()
  while not file_exists(CMD_FILE) do os.execute("sleep 0.03") end
  local f = io.open(CMD_FILE, "r"); local txt = f:read("a"); f:close()
  os.remove(CMD_FILE)
  for line in string.gmatch(txt, "[^\n]+") do
    local t = {}
    for w in string.gmatch(line, "%S+") do t[#t + 1] = w end
    if #t > 0 then queue[#queue + 1] = t end
  end
end

local function ack()
  local f = io.open(ACK_FILE .. ".tmp", "w"); f:write(table.concat(out, "\n") .. "\n"); f:close()
  os.rename(ACK_FILE .. ".tmp", ACK_FILE)
  out = {}
end

-- devolve true se a acao consome quadros (e o frame atual deve seguir)
local function start(t)
  local c = t[1]
  if c == "press" or c == "combo" then
    local hold = tonumber(t[3] or 6); local after = tonumber(t[4] or 20)
    cur = { frames = hold, keys = keymask(t[2]), after = after }
    emu:setKeys(cur.keys)
    return true
  elseif c == "hold" then
    cur = { frames = tonumber(t[3]), keys = keymask(t[2]), after = 0 }
    emu:setKeys(cur.keys)
    return true
  elseif c == "wait" then
    cur = { frames = tonumber(t[2]), keys = 0, after = 0 }
    emu:setKeys(0)
    return true
  elseif c == "shot" then emu:screenshot(t[2])
  elseif c == "save" then emu:saveStateFile(t[2], 31)
  elseif c == "load" then emu:loadStateFile(t[2], 29)
  elseif c == "r8" then out[#out + 1] = string.format("%s=%d", t[2], emu:read8(tonumber(t[2])))
  elseif c == "r16" then out[#out + 1] = string.format("%s=%d", t[2], emu:read16(tonumber(t[2])))
  elseif c == "r32" then out[#out + 1] = string.format("%s=%d", t[2], emu:read32(tonumber(t[2])))
  elseif c == "w8" then emu:write8(tonumber(t[2]), tonumber(t[3]))
  elseif c == "w16" then emu:write16(tonumber(t[2]), tonumber(t[3]))
  elseif c == "w32" then emu:write32(tonumber(t[2]), tonumber(t[3]))
  elseif c == "range" then
    local s = emu:readRange(tonumber(t[2]), tonumber(t[3]))
    out[#out + 1] = t[2] .. "=" .. (s:gsub(".", function(ch) return string.format("%02x", string.byte(ch)) end))
  elseif c == "quit" then ack(); os.exit(0)
  else out[#out + 1] = "ERR unknown " .. c end
  return false
end

callbacks:add("frame", function()
  if cur then
    cur.frames = cur.frames - 1
    if cur.frames > 0 then return end
    if cur.after and cur.after > 0 then
      emu:setKeys(0); cur.frames = cur.after; cur.after = 0; cur.keys = 0
      return
    end
    emu:setKeys(0); cur = nil
  end
  while true do
    if #queue == 0 then
      ack()
      load_cmds()
    end
    local t = table.remove(queue, 1)
    if start(t) then return end
  end
end)
