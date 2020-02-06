import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing

options = VarParsing ('analysis')
options.parseArguments()
process = cms.Process("ANALYSIS")


# import of standard configurations
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.MessageLogger.cerr.FwkReport.reportEvery = 100

# Input source
process.source = cms.Source("LHESource",
  #  duplicateCheckMode = cms.untracked.string('noDuplicateCheck'),
    fileNames = cms.untracked.vstring(options.inputFiles
    #    'file:/eos/user/g/gkole/PostDoc/MC_Contact/Powheg/master_vs_UL2019/VBF_master/cmsgrid_final.lhe'
    # 'file:/afs/cern.ch/work/c/covarell/powheg/POWHEG-BOX/VBF_H/testMSTW/pwgevents.lhe',    
#'/store/user/covarell//Gen/testMGOld/testMGOld_6.root',
#'/store/user/covarell//Gen/testMGOld/testMGOld_7.root',
#'/store/user/covarell//Gen/testMGOld/testMGOld_8.root',
#'/store/user/covarell//Gen/testMGOld/testMGOld_9.root',
#         '/store/lhe/5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_10212.lhe',
#         '/store/lhe/5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_10213.lhe',
#         '/store/lhe/5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_10214.lhe',
#         '/store/lhe/5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_10215.lhe',
#         '/store/lhe/5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_10216.lhe',
#         '/store/lhe/5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_10217.lhe',
#         '/store/lhe/5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_10218.lhe',
#         '/store/lhe/5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_10219.lhe',
#         '/store/lhe/5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_10220.lhe',
#         '/store/lhe/5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_10221.lhe',
#         '/store/lhe/5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_10222.lhe',
#         '/store/lhe/5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_10223.lhe',
#         '/store/lhe/5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_10224.lhe',
#         '/store/lhe/5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_10225.lhe',
#         '/store/lhe/5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_10226.lhe',
#         '/store/lhe/5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_10227.lhe',
#         '/store/lhe/5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_10228.lhe',
#         '/store/lhe/5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_10229.lhe',
#         '/store/lhe/5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_10230.lhe',
#         '/store/lhe/5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_10231.lhe',
#         '/store/lhe/5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_10232.lhe',
#         '/store/lhe/5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_10233.lhe',
#         '/store/lhe/5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_10234.lhe',
#         '/store/lhe/5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_10235.lhe',
#         '/store/lhe/5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_10236.lhe',
#         '/store/lhe/5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_10237.lhe',
#         '/store/lhe/5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_10238.lhe',
#         '/store/lhe/5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_10239.lhe',
#         '/store/lhe/5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_10240.lhe',
#         '/store/lhe/5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_10241.lhe',
#         '/store/lhe/5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_10242.lhe',
#         '/store/lhe/5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_10243.lhe',
#         '/store/lhe/5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_10244.lhe',
#         '/store/lhe/5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_10245.lhe',
#         '/store/lhe/5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_10246.lhe',
#         '/store/lhe/5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_10247.lhe',
#         '/store/lhe/5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_10248.lhe',
#         '/store/lhe/5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_10249.lhe',
#         '/store/lhe/5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_10250.lhe',
#         '/store/lhe/5591/DYJetsToLL_M-50_8TeV-madgraph-tarball_10251.lhe'

   )
)

# Other statements
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:mc', '')

process.Test = cms.EDAnalyzer("LHEEventAnalyzer",
                              # HistOutFile = cms.untracked.string('multMGOld.root'),
                              HistOutFile = cms.untracked.string(options.outputFile),  
                              theSrc = cms.untracked.string('source')                           
)

process.p1 = cms.Path(process.Test)

