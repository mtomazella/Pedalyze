import { invoke } from '@tauri-apps/api'
import { PedalyzePreset } from './types'
export * from './types'

export const usePresets = () => {
  const formatForRust = ({}: PedalyzePreset) => ({})

  const upload = (routine: PedalyzePreset | undefined) => {
    if (!routine) return
    invoke('upload_routine', { routine: formatForRust(routine) })
  }

  const save = (routine: PedalyzePreset | undefined) => {
    if (!routine) return
    if (
      !(
        typeof window !== 'undefined' &&
        window !== undefined &&
        window.__TAURI_IPC__ !== undefined
      )
    )
      return

    invoke('save_routine', {
      routine: formatForRust(routine),
    })
  }

  return {
    upload,
    save,
  }
}
