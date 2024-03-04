import { invoke } from '@tauri-apps/api'

export type ClientConfigurations = Record<string, any>

type UseConfigReturn = {
  fetch: () => Promise<ClientConfigurations>
  update: (config: Partial<ClientConfigurations>) => Promise<void>
}

export const useConfig = (): UseConfigReturn => {
  const fetch = async () => {
    return invoke('get_config') as ClientConfigurations
  }

  const update = async () => {
    return
  }

  return { fetch, update }
}
