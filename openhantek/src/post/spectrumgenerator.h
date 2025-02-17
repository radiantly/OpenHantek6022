// SPDX-License-Identifier: GPL-2.0+

#pragma once

#include <vector>

#include <QMutex>
#include <QThread>
#include <memory>

#include <fftw3.h>

#include "dsosamples.h"
#include "postprocessingsettings.h"
#include "ppresult.h"
#include "utils/printutils.h"

#include "processor.h"

class DsoSettings;
struct DsoSettingsScope;

/// \brief Analyzes the data from the dso.
/// Calculates the spectrum and various data about the signal and saves the
/// time-/frequencysteps between two values.
class SpectrumGenerator : public Processor {

  public:
    SpectrumGenerator( const DsoSettingsScope *scope, const DsoSettingsPostProcessing *postprocessing );
    ~SpectrumGenerator() override;

  private:
    const DsoSettingsScope *scope;
    const DsoSettingsPostProcessing *post;
    Dso::WindowFunction previousWindowFunction = Dso::WindowFunction( -1 ); ///< The previously used dft window function
    std::vector< double > window;                                           ///< storage for the tapering window
    fftw_plan fftPlan_R2HC = nullptr;
    fftw_plan fftPlan_HC2R = nullptr;
    // Processor interface
    void process( PPresult *data ) override;
};
